execute( Chuck_VM * vm, Chuck_VM_Shred * shred )
{
    t_CKUINT *& reg_sp = (t_CKUINT *&)shred->reg->sp;


    if( *(reg_sp-2) >= *(reg_sp-1) )
        shred->next_pc = m_val;
    else
    {

        instantiate_object( vm, shred, type );
    }
}
