lisp_merge_config (apr_pool_t * pool, void * base_cfg, void * add_cfg)
{
  return
    ((SERVER_SPECIFIED_P (CFG (add_cfg)))
          ? (copy_lisp_cfg (pool, add_cfg))
	       : (SERVER_SPECIFIED_P (CFG (base_cfg)))
	            ? (copy_lisp_cfg (pool, base_cfg))
		         : (default_lisp_cfg (pool)));
}
