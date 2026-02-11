Relaxed(dir_t dir)
{
   if(total_reconfig_needed)
      ReconfigTotal();

   if(one[dir].rate==0 && total[dir].rate==0)
      return true;
   one  [dir].AdjustTime();
   total[dir].AdjustTime();

   if(total[dir].rate>0 && total[dir].pool < total[dir].pool_max/2)
      return false;
   if(one[dir].rate>0 && one[dir].pool < one[dir].pool_max/2)
      return false;
   return true;
}
