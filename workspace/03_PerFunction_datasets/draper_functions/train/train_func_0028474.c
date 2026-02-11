mlx4_cmd_wait(struct mlx4_dev *dev, u64 in_param, u64 *out_param,
			 int out_is_imm, u32 in_modifier, u8 op_modifier,
			 u16 op, unsigned long timeout)
{
	struct mlx4_cmd *cmd = &mlx4_priv(dev)->cmd;
	struct mlx4_cmd_context *context;
	long ret_wait;
	int err = 0;

	down(&cmd->event_sem);

	spin_lock(&cmd->context_lock);
	BUG_ON(cmd->free_head < 0);
	context = &cmd->context[cmd->free_head];
	context->token += cmd->token_mask + 1;
	cmd->free_head = context->next;
	spin_unlock(&cmd->context_lock);

	if (out_is_imm && !out_param) {
		mlx4_err(dev, "response expected while output mailbox is NULL for command 0x%x\n",
			 op);
		err = -EINVAL;
		goto out;
	}

	reinit_completion(&context->done);

	err = mlx4_cmd_post(dev, in_param, out_param ? *out_param : 0,
			    in_modifier, op_modifier, op, context->token, 1);
	if (err)
		goto out_reset;

	if (op == MLX4_CMD_SENSE_PORT) {
		ret_wait =
			wait_for_completion_interruptible_timeout(&context->done,
								  msecs_to_jiffies(timeout));
		if (ret_wait < 0) {
			context->fw_status = 0;
			context->out_param = 0;
			context->result = 0;
		}
	} else {
		ret_wait = (long)wait_for_completion_timeout(&context->done,
							     msecs_to_jiffies(timeout));
	}
	if (!ret_wait) {
		mlx4_warn(dev, "command 0x%x timed out (go bit not cleared)\n",
			  op);
		if (op == MLX4_CMD_NOP) {
			err = -EBUSY;
			goto out;
		} else {
			err = -EIO;
			goto out_reset;
		}
	}

	err = context->result;
	if (err) {


		if (op == MLX4_CMD_SET_PORT &&
		    (in_modifier == 1 || in_modifier == 2) &&
		    op_modifier == MLX4_SET_PORT_IB_OPCODE &&
		    context->fw_status == CMD_STAT_BAD_SIZE)
			mlx4_dbg(dev, "command 0x%x failed: fw status = 0x%x\n",
				 op, context->fw_status);
		else
			mlx4_err(dev, "command 0x%x failed: fw status = 0x%x\n",
				 op, context->fw_status);
		if (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
			err = mlx4_internal_err_ret_value(dev, op, op_modifier);
		else if (mlx4_closing_cmd_fatal_error(op, context->fw_status))
			goto out_reset;

		goto out;
	}

	if (out_is_imm)
		*out_param = context->out_param;

out_reset:
	if (err)
		err = mlx4_cmd_reset_flow(dev, op, op_modifier, err);
out:
	spin_lock(&cmd->context_lock);
	context->next = cmd->free_head;
	cmd->free_head = context - cmd->context;
	spin_unlock(&cmd->context_lock);

	up(&cmd->event_sem);
	return err;
}
