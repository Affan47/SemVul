cmsGDBAddPoint(cmsHANDLE hGBD, const cmsCIELab* Lab)
{
    cmsGDB* gbd = (cmsGDB*) hGBD;
    cmsGDBPoint* ptr;
    cmsSpherical sp;


    ptr = GetPoint(gbd, Lab, &sp);
    if (ptr == NULL) return FALSE;


    if (ptr ->Type == GP_EMPTY) {

        ptr -> Type = GP_SPECIFIED;
        ptr -> p    = sp;
    }
    else {


        if (sp.r > ptr -> p.r) {

                ptr -> Type = GP_SPECIFIED;
                ptr -> p    = sp;
        }
    }

    return TRUE;
}
