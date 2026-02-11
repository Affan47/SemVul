run_scripts(JCR *jcr, alist *runscripts, const char *label)
{
   Dmsg2(200, "runscript: running all RUNSCRIPT object (%s) JobStatus=%c\n", label, jcr->JobStatus);

   RUNSCRIPT *script;
   bool runit;

   int when;

   if (strstr(label, NT_("Before"))) {
      when = SCRIPT_Before;
   } else if (bstrcmp(label, NT_("ClientAfterVSS"))) {
      when = SCRIPT_AfterVSS;
   } else {
      when = SCRIPT_After;
   }

   if (runscripts == NULL) {
      Dmsg0(100, "runscript: WARNING RUNSCRIPTS list is NULL\n");
      return 0;
   }

   foreach_alist(script, runscripts) {
      Dmsg2(200, "runscript: try to run %s:%s\n", NPRT(script->target), NPRT(script->command));
      runit = false;

      if ((script->when & SCRIPT_Before) && (when & SCRIPT_Before)) {
         if ((script->on_success &&
              (jcr->JobStatus == JS_Running || jcr->JobStatus == JS_Created))
            || (script->on_failure &&
                (job_canceled(jcr) || jcr->JobStatus == JS_Differences))
            )
         {
            Dmsg4(200, "runscript: Run it because SCRIPT_Before (%s,%i,%i,%c)\n",
                  script->command, script->on_success, script->on_failure,
                  jcr->JobStatus );
            runit = true;
         }
      }

      if ((script->when & SCRIPT_AfterVSS) && (when & SCRIPT_AfterVSS)) {
         if ((script->on_success && (jcr->JobStatus == JS_Blocked))
            || (script->on_failure && job_canceled(jcr))
            )
         {
            Dmsg4(200, "runscript: Run it because SCRIPT_AfterVSS (%s,%i,%i,%c)\n",
                  script->command, script->on_success, script->on_failure,
                  jcr->JobStatus );
            runit = true;
         }
      }

      if ((script->when & SCRIPT_After) && (when & SCRIPT_After)) {
         if ((script->on_success &&
              (jcr->JobStatus == JS_Terminated || jcr->JobStatus == JS_Warnings))
            || (script->on_failure &&
                (job_canceled(jcr) || jcr->JobStatus == JS_Differences))
            )
         {
            Dmsg4(200, "runscript: Run it because SCRIPT_After (%s,%i,%i,%c)\n",
                  script->command, script->on_success, script->on_failure,
                  jcr->JobStatus );
            runit = true;
         }
      }

      if (!script->is_local()) {
         runit = false;
      }


      if (runit) {
         script->run(jcr, label);
      }
   }
   return 1;
}
