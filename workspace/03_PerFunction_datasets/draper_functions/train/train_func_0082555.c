cmsPipelineUnlinkStage(cmsPipeline* lut, cmsStageLoc loc, cmsStage** mpe)
{
    cmsStage *Anterior, *pt, *Last;
    cmsStage *Unlinked = NULL;


    if (lut ->Elements == NULL) {
        if (mpe) *mpe = NULL;
        return;
    }


    switch (loc) {

        case cmsAT_BEGIN:
            {
                cmsStage* elem = lut ->Elements;

                lut ->Elements = elem -> Next;
                elem ->Next = NULL;
                Unlinked = elem;

            }
            break;

        case cmsAT_END:
            Anterior = Last = NULL;
            for (pt = lut ->Elements;
                pt != NULL;
                pt = pt -> Next) {
                    Anterior = Last;
                    Last = pt;
            }

            Unlinked = Last;


            if (Anterior)
                Anterior ->Next = NULL;
            else
                lut ->Elements = NULL;
            break;
        default:;
    }

    if (mpe)
        *mpe = Unlinked;
    else
        cmsStageFree(Unlinked);

    BlessLUT(lut);
}
