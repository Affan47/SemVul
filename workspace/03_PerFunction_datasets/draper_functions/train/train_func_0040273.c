mutexNew(int id)
{
     if (id >=0 && id < M_MAX && _mutexes[id] == NULL) {
         _mutexes[id] = g_mutex_new();
	     return RC_OK;
     }
     return RC_NOK;
}
