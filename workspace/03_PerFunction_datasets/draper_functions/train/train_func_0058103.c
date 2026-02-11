c7200_init_instance(vm_instance_t *vm)
{
   c7200_t *router = VM_C7200(vm);

   switch(router->npe_driver->npe_family) {
      case C7200_NPE_FAMILY_MIPS:
         return(c7200m_init_instance(router));

      case C7200_NPE_FAMILY_PPC:
         return(c7200p_init_instance(router));

      default:
         vm_error(router->vm,"unsupported NPE family %d",
                  router->npe_driver->npe_family);
         return(-1);
   }
}
