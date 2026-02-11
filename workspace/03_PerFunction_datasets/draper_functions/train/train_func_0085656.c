vpi_get_systf_info(vpiHandle object,
 p_vpi_systf_data systf_data_p)
{
 int32 stf_ind;
 struct h_t *hp;
 struct hrec_t *hrp;
 p_vpi_systf_data tfdatp;
 struct systftab_t *stftabp;

 __last_eip = NULL;
 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_get_systf_info", hp)) return;
 hrp = hp->hrec;
 if (hrp->htyp != vpiUserSystf && hrp->htyp != vpiSysFuncCall
  && hrp->htyp != vpiSysTaskCall)
  {
   __vpi_err(1821, vpiError,
    "vpi_get_systf_info requires vpiUserSystf or vpiSys[Func|Task]Call handle");
   return;
  }
 stf_ind = hrp->hi - (__last_veriusertf + 1);
 stftabp = &(__systftab[stf_ind]);
 tfdatp = (p_vpi_systf_data) stftabp->vpi_sytfdat;
 *(systf_data_p) = *(tfdatp);
}
