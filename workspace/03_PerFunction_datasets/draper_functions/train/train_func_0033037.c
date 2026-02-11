GDALUnloadAPIPROXYDriver(GDALDriver* poDriver)
{
    if( bRecycleChild )
    {

        bRecycleChild = FALSE;
        for(int i=0;i<nMaxRecycled;i++)
        {
            if( aspRecycled[i] != NULL )
            {
                GDALServerSpawnAsyncFinish(aspRecycled[i]);
                aspRecycled[i] = NULL;
            }
        }
    }
    poAPIPROXYDriver = NULL;
}
