main(int argc, char *argv[])
{
   int ret = 0;

   DENTER_MAIN(TOP_LAYER, "test_resource_utilization");

   sge_mt_init();

   lInit(nmv);

   ret += test_normal_utilization();
   ret += test_extensive_utilization();

   if (ret != 0) {
      printf("\ntest failed!\n");
   }

   return ret;
}
