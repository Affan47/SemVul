alloc_cmd(struct mlx5_cmd *cmd,
					   struct mlx5_cmd_msg *in,
					   struct mlx5_cmd_msg *out,
					   void *uout, int uout_size,
					   mlx5_cmd_cbk_t cbk,
					   void *context, int page_queue)
{
	gfp_t alloc_flags = cbk ? GFP_ATOMIC : GFP_KERNEL;
	struct mlx5_cmd_work_ent *ent;

	ent = kzalloc(sizeof(*ent), alloc_flags);
	if (!ent)
		return ERR_PTR(-ENOMEM);

	ent->in		= in;
	ent->out	= out;
	ent->uout	= uout;
	ent->uout_size	= uout_size;
	ent->callback	= cbk;
	ent->context	= context;
	ent->cmd	= cmd;
	ent->page_queue = page_queue;

	return ent;
}
