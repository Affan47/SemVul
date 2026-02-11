JAM_GetSubfield( s_JamSubPacket* SubPack_PS )
{
    static s_JamSubPacket* LastPack_PS = NULL;
    static ulong           NextIndex_I = 0;

    if ( SubPack_PS ) {
	LastPack_PS = SubPack_PS;
	NextIndex_I = 0;
    }

    if ( NextIndex_I < LastPack_PS->NumFields )
	return LastPack_PS->Fields[ NextIndex_I++ ];

    return NULL;
}
