ppc32_set_ia(u_char **ptr,m_uint32_t new_ia)
{
   amd64_mov_membase_imm(*ptr,AMD64_R15,OFFSET(cpu_ppc_t,ia),new_ia,4);
}
