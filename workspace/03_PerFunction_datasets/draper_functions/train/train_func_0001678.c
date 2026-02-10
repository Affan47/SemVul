_ecore_evas_unref(Ecore_Evas *ee)
{
   ee->refcount--;
   if (ee->refcount == 0)
     {
        if (ee->deleted) _ecore_evas_free(ee);
     }
   else if (ee->refcount < -1)
     ERR("Ecore_Evas %p->refcount=%d < 0", ee, ee->refcount);
}
