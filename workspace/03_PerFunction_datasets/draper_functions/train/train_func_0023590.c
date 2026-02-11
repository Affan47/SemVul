visit_field(const glsl_type *type, const char *name,
                            bool row_major, const glsl_type *record_type)
   {
      assert(this->index < this->num_variables);

      gl_uniform_buffer_variable *v = &this->variables[this->index++];

      v->Name = ralloc_strdup(mem_ctx, name);
      v->Type = type;
      v->RowMajor = row_major;

      if (this->is_array_instance) {
         v->IndexName = ralloc_strdup(mem_ctx, name);

         char *open_bracket = strchr(v->IndexName, '[');
         assert(open_bracket != NULL);

         char *close_bracket = strchr(open_bracket, ']');
         assert(close_bracket != NULL);


         unsigned len = strlen(close_bracket + 1) + 1;

         memmove(open_bracket, close_bracket + 1, len);
     } else {
         v->IndexName = v->Name;
      }

      const unsigned alignment = record_type
	 ? record_type->std140_base_alignment(v->RowMajor)
	 : type->std140_base_alignment(v->RowMajor);
      unsigned size = type->std140_size(v->RowMajor);

      this->offset = glsl_align(this->offset, alignment);
      v->Offset = this->offset;
      this->offset += size;


      this->buffer_size = glsl_align(this->offset, 16);
   }
