_init_post(const ecs_cmd_t *cmd)
{
  ecs_post_t     *cas_post;


  cas_post = ecs_post__cree_cas(cmd->nom_cas);

  if (!strcmp(cmd->post_err, "ens"))
    cas_post->opt_ens[ECS_POST_TYPE_ERREUR] = true;
  if (!strcmp(cmd->post_vol, "ens"))
    cas_post->opt_ens[ECS_POST_TYPE_VOLUME] = true;

#if defined(HAVE_CGNS)
  if (!strcmp(cmd->post_err, "cgns"))
    cas_post->opt_cgns[ECS_POST_TYPE_ERREUR] = true;
  if (!strcmp(cmd->post_vol, "cgns"))
    cas_post->opt_cgns[ECS_POST_TYPE_VOLUME] = true;
#endif

#if defined(HAVE_MED)
  if (!strcmp(cmd->post_err, "med"))
    cas_post->opt_med[ECS_POST_TYPE_ERREUR] = true;
  if (!strcmp(cmd->post_vol, "med"))
    cas_post->opt_med[ECS_POST_TYPE_VOLUME] = true;
#endif

  return cas_post;
}
