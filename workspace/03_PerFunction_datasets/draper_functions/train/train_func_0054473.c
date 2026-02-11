main(int argc, char **argv) {
  AB_BANKING *ab;
  int rv;
  AB_ACCOUNT *a;
  GWEN_GUI *gui;

  gui=GWEN_Gui_CGui_new();
  GWEN_Gui_SetGui(gui);

  ab=AB_Banking_new("tutorial3", 0, 0);


  rv=AB_Banking_Init(ab);
  if (rv) {
    fprintf(stderr, "Error on init (%d)\n", rv);
    return 2;
  }
  fprintf(stderr, "AqBanking successfully initialized.\n");


  rv=AB_Banking_OnlineInit(ab);
  if (rv) {
    fprintf(stderr, "Error on init of online modules (%d)\n", rv);
    return 2;
  }


  a=AB_Banking_FindAccount(ab,
                           "aqhbci",
                           "de",
                           "200*",
                           "*",
                           "*");
  if (a) {
    AB_JOB_LIST2 *jl;
    AB_JOB *j;
    AB_IMEXPORTER_CONTEXT *ctx;


    j=AB_JobGetTransactions_new(a);


    rv=AB_Job_CheckAvailability(j);
    if (rv) {
      fprintf(stderr, "Job is not available (%d)\n", rv);
      return 2;
    }


    jl=AB_Job_List2_new();


    AB_Job_List2_PushBack(jl, j);


    ctx=AB_ImExporterContext_new();


    rv=AB_Banking_ExecuteJobs(ab, jl, ctx);
    if (rv) {
      fprintf(stderr, "Error on executeQueue (%d)\n", rv);
      return 2;
    }
    else {
      AB_IMEXPORTER_ACCOUNTINFO *ai;

      ai=AB_ImExporterContext_GetFirstAccountInfo(ctx);
      while(ai) {
        const AB_TRANSACTION *t;

        t=AB_ImExporterAccountInfo_GetFirstTransaction(ai);
        while(t) {
          const AB_VALUE *v;

          v=AB_Transaction_GetValue(t);
          if (v) {
            const GWEN_STRINGLIST *sl;
            const char *purpose;


            sl=AB_Transaction_GetPurpose(t);
            if (sl)
              purpose=GWEN_StringList_FirstString(sl);
            else
              purpose="";

            fprintf(stderr, " %-32s (%.2f %s)\n",
                    purpose,
		    AB_Value_GetValueAsDouble(v),
                    AB_Value_GetCurrency(v));
          }
          t=AB_ImExporterAccountInfo_GetNextTransaction(ai);
        }
        ai=AB_ImExporterContext_GetNextAccountInfo(ctx);
      }
    }

    AB_Job_free(j);
  }
  else {
    fprintf(stderr, "No account found.\n");
  }


  rv=AB_Banking_OnlineFini(ab);
  if (rv) {
    fprintf(stderr, "ERROR: Error on deinit online modules (%d)\n", rv);
    return 3;
  }


  rv=AB_Banking_Fini(ab);
  if (rv) {
    fprintf(stderr, "ERROR: Error on deinit (%d)\n", rv);
    return 3;
  }
  AB_Banking_free(ab);

  return 0;
}
