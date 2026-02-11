FCEUI_NTSCINC(void)
{
                   if(ntsccol && FCEUGameInfo->type!=GIT_VSUNI && !PAL && FCEUGameInfo->type!=GIT_NSF)
                     if(controlselect)
                     {
                      if(controllength)
                      {
                       switch(controlselect)
                       {
                        case 1:ntschue++;
                               if(ntschue>128) ntschue=128;
                               CalculatePalette();
                               break;
                        case 2:ntsctint++;
                               if(ntsctint>128) ntsctint=128;
                               CalculatePalette();
                               break;
                       }
                      }
                      controllength=360;
                     }
}
