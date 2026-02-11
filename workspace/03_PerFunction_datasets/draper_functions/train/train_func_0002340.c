wf_clo(p_wf)
p_wf_t p_wf;
{
 wf_check(p_wf);
 if ( p_wf->wf_iserr) return;
 as_cold(p_wf->wf_isope,"wf_clo: WF is not open.");
 if (fflush(p_wf->wf_pfile) != FFLUSH_S)
    wf_errlg(p_wf,"wf_clo: Error fflush()ing output file.");
 if (fclose(p_wf->wf_pfile) == FCLOSE_F)
    wf_errlg(p_wf,"wf_clo: Error fclose()ing output file.");
 p_wf->wf_isope=FALSE;
 p_wf->wf_pfile=NULL;
 wf_check(p_wf);
}
