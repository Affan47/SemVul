x86_disasm_forward( unsigned char *buf, unsigned int buf_len,
                        uint32_t buf_rva, unsigned int offset,
                        DISASM_CALLBACK func, void *arg,
                        DISASM_RESOLVER resolver, void *r_arg ){
        x86_insn_t insn;
        x86_op_t *op;
        int32_t next_addr;
        uint32_t next_offset;
        unsigned int size, count = 0, bytes = 0, cont = 1;

        while ( cont && bytes < buf_len ) {
                size = x86_disasm( buf, buf_len, buf_rva, offset + bytes,
                           &insn );

                if ( size ) {

                        if ( func ) {
                                (*func)( &insn, arg );
                        }
                        bytes += size;
                        count ++;
                } else {

                        bytes++;
                }

                if ( follow_insn_dest(&insn) ) {
                        op = x86_get_dest_operand( &insn );
                        next_addr = -1;


                        if ( resolver ) {
                                next_addr = resolver(op, &insn, r_arg);
                        } else {
                                next_addr = internal_resolver(op, &insn);
                        }

                        if (next_addr != -1 ) {
                                next_offset = next_addr - buf_rva;

                                if ( next_offset >= 0 &&
                                     next_offset < buf_len ) {

                                        count += x86_disasm_forward( buf,
                                                            buf_len,
                                                            buf_rva,
                                                            next_offset,
                                                            func, arg,
                                                            resolver, r_arg );
                                } else  {

                                        x86_report_error( report_disasm_bounds,
                                                     (void*)(long)next_addr );
                                }
                        }
                }

                if ( insn_doesnt_return(&insn) ) {

                        cont = 0;
                }

		x86_oplist_free( &insn );
        }
        return( count );
}
