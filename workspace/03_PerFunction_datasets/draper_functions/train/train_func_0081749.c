syncenv_task (struct syncenv *env)
{
        struct synctask  *task = NULL;

        pthread_mutex_lock (&env->mutex);
        {
                while (list_empty (&env->runq))
                        pthread_cond_wait (&env->cond, &env->mutex);

                task = list_entry (env->runq.next, struct synctask, all_tasks);

                list_del_init (&task->all_tasks);
        }
        pthread_mutex_unlock (&env->mutex);

        return task;
}
