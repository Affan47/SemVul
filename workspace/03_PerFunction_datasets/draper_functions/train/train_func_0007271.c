PutCeosRecordStruct(CeosRecord_t *record,const void *struct_ptr)
{
    int Length;

    if(record && struct_ptr)
    {
	CeosToNative( &Length, struct_ptr, sizeof( Length ), sizeof( Length ) );
	memcpy(record->Buffer,struct_ptr,Length);
	CeosUpdateHeaderFromBuffer(record);
    }
}
