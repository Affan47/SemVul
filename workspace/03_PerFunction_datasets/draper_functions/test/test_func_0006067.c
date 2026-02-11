get_functional_weighting_parameters( double sum_of_user_functional_shares,
                                     double sum_of_project_functional_shares,
                                     double sum_of_department_functional_shares,
                                     double sum_of_job_functional_shares,
                                     double weight[] )
{
   double k_sum;
   memset(weight, 0, sizeof(double)*k_last);

   if (sconf_is()) {
      if (sum_of_user_functional_shares > 0)
         weight[k_user] = sconf_get_weight_user();
      if (sum_of_department_functional_shares > 0)
         weight[k_department] = sconf_get_weight_department();
      if (sum_of_project_functional_shares > 0)
         weight[k_project] = sconf_get_weight_project();
      if (sum_of_job_functional_shares > 0)
         weight[k_job] = sconf_get_weight_job();
      k_sum = weight[k_user] + weight[k_department] + weight[k_project] +
              weight[k_job];
   } else {
      weight[k_user] = 1;
      weight[k_department] = 1;
      weight[k_project] = 1;
      weight[k_job] = 1;
      k_sum = weight[k_user] + weight[k_department] + weight[k_project] +
              weight[k_job];
   }

   if (k_sum>0) {
      weight[k_user] /= k_sum;
      weight[k_department] /= k_sum;
      weight[k_project] /= k_sum;
      weight[k_job] /= k_sum;
   }

   return;
}
