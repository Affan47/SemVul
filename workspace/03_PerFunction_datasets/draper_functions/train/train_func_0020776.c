free_at_address_script (seg_interface_t *self, reg_t addr)
{
	script_t *script;
	VERIFY(self->mobj->type == MEM_OBJ_SCRIPT, "Trying to free a non-script!");
	script = &(self->mobj->data.script);


	if (script->marked_as_deleted)
		sm_deallocate_script(self->segmgr, script->nr);
}
