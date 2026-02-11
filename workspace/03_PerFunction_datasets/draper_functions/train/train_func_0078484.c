cmsCreate_sRGBProfileTHR(cmsContext ContextID)
{
       cmsCIExyY       D65 = { 0.3127, 0.3290, 1.0 };
       cmsCIExyYTRIPLE Rec709Primaries = {
                                   {0.6400, 0.3300, 1.0},
                                   {0.3000, 0.6000, 1.0},
                                   {0.1500, 0.0600, 1.0}
                                   };
       cmsToneCurve* Gamma22[3];
       cmsHPROFILE  hsRGB;


       Gamma22[0] = Gamma22[1] = Gamma22[2] = Build_sRGBGamma(ContextID);
       if (Gamma22[0] == NULL) return NULL;

       hsRGB = cmsCreateRGBProfileTHR(ContextID, &D65, &Rec709Primaries, Gamma22);
       cmsFreeToneCurve(Gamma22[0]);
       if (hsRGB == NULL) return NULL;

       if (!SetTextTags(hsRGB, L"sRGB built-in")) {
           cmsCloseProfile(hsRGB);
           return NULL;
       }

       return hsRGB;
}
