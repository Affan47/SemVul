qacct_usage(sge_gdi_ctx_class_t **ctx, FILE *fp)
{
   dstring ds;
   char buffer[256];

   DENTER(TOP_LAYER, "qacct_usage");

   sge_dstring_init(&ds, buffer, sizeof(buffer));

   fprintf(fp, "%s\n", feature_get_product_name(FS_SHORT_VERSION, &ds));

   fprintf(fp, "%s qacct [options]\n", MSG_HISTORY_USAGE);
   fprintf(fp, " [-ar [ar_id]]                     %s\n", MSG_HISTORY_ar_OPT_USAGE);
   fprintf(fp, " [-A account_string]               %s\n", MSG_HISTORY_A_OPT_USAGE);
   fprintf(fp, " [-b begin_time]                   %s\n", MSG_HISTORY_b_OPT_USAGE);
   fprintf(fp, " [-d days]                         %s\n", MSG_HISTORY_d_OPT_USAGE );
   fprintf(fp, " [-D [department]]                 %s\n", MSG_HISTORY_D_OPT_USAGE);
   fprintf(fp, " [-e end_time]                     %s\n", MSG_HISTORY_e_OPT_USAGE);
   fprintf(fp, " [-g [groupid|groupname]]          %s\n", MSG_HISTORY_g_OPT_USAGE );
   fprintf(fp, " [-h [host]]                       %s\n", MSG_HISTORY_h_OPT_USAGE );
   fprintf(fp, " [-help]                           %s\n", MSG_HISTORY_help_OPT_USAGE);
   fprintf(fp, " [-j [job_id|job_name|pattern]]    %s\n", MSG_HISTORY_j_OPT_USAGE);
   fprintf(fp, " [-l attr=val,...]                 %s\n", MSG_HISTORY_l_OPT_USAGE );
   fprintf(fp, " [-o [owner]]                      %s\n", MSG_HISTORY_o_OPT_USAGE);
   fprintf(fp, " [-pe [pe_name]]                   %s\n", MSG_HISTORY_pe_OPT_USAGE );
   fprintf(fp, " [-P [project]]                    %s\n", MSG_HISTORY_P_OPT_USAGE );
   fprintf(fp, " [-q [queue]]                      %s\n", MSG_HISTORY_q_OPT_USAGE );
   fprintf(fp, " [-slots [slots]]                  %s\n", MSG_HISTORY_slots_OPT_USAGE);
   fprintf(fp, " [-t taskid[-taskid[:step]]]       %s\n", MSG_HISTORY_t_OPT_USAGE );
   fprintf(fp, " [[-f] acctfile]                   %s\n", MSG_HISTORY_f_OPT_USAGE );

   fprintf(fp, "\n");
   fprintf(fp, " begin_time, end_time              %s\n", MSG_HISTORY_beginend_OPT_USAGE );
   fprintf(fp, " queue                             [cluster_queue|queue_instance|queue_domain|pattern]\n");
   if (fp==stderr) {
      SGE_EXIT((void**)ctx, 1);
   } else {
      SGE_EXIT((void**)ctx, 0);
   }

   DRETURN_VOID;
}
