_e_mod_comp_render_queue(E_Comp *c)
{

   if (!c) return;

   if (_comp_mod->conf->lock_fps)
     {
        if (c->render_animator)
          {
             c->render_overflow = OVER_FLOW;
             return;
          }
        c->render_animator = ecore_animator_add(_e_mod_comp_cb_animator, c);
     }
   else
     {
        if (c->update_job)
          {
             DBG("UPDATE JOB DEL...\n");
             ecore_job_del(c->update_job);
             c->update_job = NULL;
             c->render_overflow = 0;
          }
        DBG("UPDATE JOB ADD...\n");
        c->update_job = ecore_job_add(_e_mod_comp_cb_job, c);
     }
}
