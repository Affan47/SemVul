chk_cnvt_fd_modes(char *os_mode, char *ver_mode)
{

 strcpy(os_mode, ver_mode);

 if (strcmp(ver_mode, "r") == 0) return(TRUE);
 if (strcmp(ver_mode, "rb") == 0) { strcpy(os_mode, "r"); return(TRUE); }
 if (strcmp(ver_mode, "w") == 0) return(TRUE);
 if (strcmp(ver_mode, "wb") == 0) { strcpy(os_mode, "w"); return(TRUE); }
 if (strcmp(ver_mode, "a") == 0) return(TRUE);
 if (strcmp(ver_mode, "ab") == 0) { strcpy(os_mode, "a"); return(TRUE); }
 if (strcmp(ver_mode, "r+") == 0) return(TRUE);
 if (strcmp(ver_mode, "r+b") == 0) { strcpy(os_mode, "r+"); return(TRUE); }
 if (strcmp(ver_mode, "rb+") == 0) { strcpy(os_mode, "r+"); return(TRUE); }
 if (strcmp(ver_mode, "w+") == 0) return(TRUE);
 if (strcmp(ver_mode, "w+b") == 0) { strcpy(os_mode, "w+"); return(TRUE); }
 if (strcmp(ver_mode, "wb+") == 0) { strcpy(os_mode, "w+"); return(TRUE); }
 if (strcmp(ver_mode, "a+") == 0) return(TRUE);
 if (strcmp(ver_mode, "a+b") == 0) { strcpy(os_mode, "a+"); return(TRUE); }
 if (strcmp(ver_mode, "ab+") == 0) { strcpy(os_mode, "a+"); return(TRUE); }
 return(FALSE);
}
