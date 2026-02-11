stalls()
{

    bool exec =
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == MUL_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == DIV_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == ADD_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == SUB_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == AND_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == OR_OP   ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == XOR_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == LSC_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == LDI_OP  ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == LOAD_OP ) ||
      ( ( pipeline[ 2 ].front_2 & INSTRUCTION_MASK ) == LLC_OP  );


    bool deco =
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == MUL_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == DIV_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == ADD_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == SUB_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == AND_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == OR_OP  ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == XOR_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == LDI_OP ) ||
      ( ( pipeline[ 1 ].front_2 & INSTRUCTION_MASK ) == STI_OP );

    if ( exec && deco )
    {
        BYTE result =    ( pipeline[ 2 ].front_2 & 0x0f00 ) >> 8;
        BYTE operand_1 = ( pipeline[ 1 ].front_2 & 0x00f0 ) >> 4;
        BYTE operand_2 = ( pipeline[ 1 ].front_2 & 0x000f );

        if ( result && ( operand_1 == result || operand_2 == result ) )
        {
            #if 0
            cout << "This is a stall - R" << ( (int) result )
                 << " used in next instruction, at about PC=0x"
                 << hex << setw( 4 ) << setfill( '0' ) << pc
                 << " instruction 0x" << hex << setw( 4 ) << setfill( '0' ) << pipeline[ 1 ].front_2
                 << " depends on 0x"  << hex << setw( 4 ) << setfill( '0' ) << pipeline[ 2 ].front_2
                 << endl;
            #endif
            return( 1 );
        }
    }
    return( 0 );
}
