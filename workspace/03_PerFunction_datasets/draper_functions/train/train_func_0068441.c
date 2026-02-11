asm_SetWordMemory (mem_tab, addr, data)

struct uttyp *mem_tab;
unsigned int  addr   ;
unsigned int  data   ;

  {
  struct uttyp  *pt_mem  = NULL;
  unsigned int   offset  = 0   ;
  struct uttyp  *pt_tab  = NULL;
  unsigned char *pt_dat  = NULL;
  unsigned char *pt_flg  = NULL;


  addr = addr & 0xfffffffc;


  pt_mem  = asm_fndmemtab (mem_tab, addr);
  if (pt_mem == NULL)
    {
    mem_tab = asm_addmemtab (mem_tab, addr);
    pt_mem  = asm_fndmemtab (mem_tab, addr);
    }


  offset =                   addr % ASM_BLC__MEMORY;
  pt_tab = (struct uttyp  *) pt_mem->DAT2.VPNT     ;

  pt_dat = (unsigned char *) pt_tab->DAT1.VPNT     ;
  pt_flg = (unsigned char *) pt_tab->DAT2.VPNT     ;

  pt_dat [offset    ] = (data      ) & 0x000000ff;
  pt_dat [offset + 1] = (data >>  8) & 0x000000ff;
  pt_dat [offset + 2] = (data >> 16) & 0x000000ff;
  pt_dat [offset + 3] = (data >> 24) & 0x000000ff;

  pt_flg [offset    ] =  1                       ;
  pt_flg [offset + 1] =  1                       ;
  pt_flg [offset + 2] =  1                       ;
  pt_flg [offset + 3] =  1                       ;

  return (mem_tab);
  }
