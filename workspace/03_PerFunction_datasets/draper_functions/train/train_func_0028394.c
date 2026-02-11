visit_field(const glsl_type *type, const char *name,
                            bool row_major)
   {
      assert(!type->is_record());
      assert(!(type->is_array() && type->fields.array->is_record()));
      assert(!type->is_interface());
      assert(!(type->is_array() && type->fields.array->is_interface()));

      (void) row_major;


      const unsigned values = values_for_type(type);
      if (type->contains_sampler()) {
	 this->num_shader_samplers +=
	    type->is_array() ? type->array_size() : 1;
      } else {


	 if (!is_ubo_var)
	    this->num_shader_uniform_components += values;
      }


      unsigned id;
      if (this->map->get(id, name))
	 return;

      this->map->put(this->num_active_uniforms, name);


      this->num_active_uniforms++;
      this->num_values += values;
   }
