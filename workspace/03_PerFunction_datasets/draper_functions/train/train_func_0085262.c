ecs_descr_chaine__trouve_num(ecs_descr_t        *descr_tete,
                             const ecs_descr_t  *descr_rech)
{
  ecs_descr_t  *ptr_descr;


  assert(descr_tete != NULL && descr_rech != NULL);

  ptr_descr = descr_tete;

  while (   ptr_descr != NULL
         && ecs_descr__compare(ptr_descr, descr_rech ) == false)
    ptr_descr = ptr_descr->l_descr_sui;

  if (ptr_descr != NULL) {

    return ptr_descr->num;

  }
  else {

    return ECS_DESCR_NUM_NUL;

  }
}
