sm_put_heap (seg_manager_t* self, reg_t reg, gint16 value ) {
	mem_obj_t* mem_obj;
	mem_obj_enum mem_type;

	VERIFY( sm_check (self, reg.segment), "Invalid seg id" );
	mem_obj = self->heap[reg.segment];
	mem_type = mem_obj->type;

	switch( mem_type ) {
	case MEM_OBJ_SCRIPT:
		VERIFY( reg.offset + 1 < mem_obj->data.script.buf_size, "invalid offset" );
		mem_obj->data.script.buf[reg.offset] = value & 0xff;
		mem_obj->data.script.buf[reg.offset + 1] = value >> 8;
		break;
	case MEM_OBJ_CLONES:
		sciprintf( "memcpy for clones haven't been implemented\n" );
		break;
	default:
		sciprintf( "unknown mem obj type\n" );
		break;
	}
}
