vmw_cmd_switch_backup(struct vmw_private *dev_priv,
				 struct vmw_sw_context *sw_context,
				 enum vmw_res_type res_type,
				 const struct vmw_user_resource_conv
				 *converter,
				 uint32_t *res_id,
				 uint32_t *buf_id,
				 unsigned long backup_offset)
{
	struct vmw_resource_val_node *val_node;
	int ret;

	ret = vmw_cmd_res_check(dev_priv, sw_context, res_type,
				converter, res_id, &val_node);
	if (ret)
		return ret;

	return vmw_cmd_res_switch_backup(dev_priv, sw_context, val_node,
					 buf_id, backup_offset);
}
