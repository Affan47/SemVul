handle_samplers(const glsl_type *base_type,
                        struct gl_uniform_storage *uniform)
   {
      if (base_type->is_sampler()) {
         uniform->sampler[shader_type].index = this->next_sampler;
         uniform->sampler[shader_type].active = true;


         this->next_sampler +=
               MAX2(1, uniform->array_elements);

         const gl_texture_index target = base_type->sampler_index();
         const unsigned shadow = base_type->sampler_shadow;
         for (unsigned i = uniform->sampler[shader_type].index;
              i < MIN2(this->next_sampler, MAX_SAMPLERS);
              i++) {
            this->targets[i] = target;
            this->shader_samplers_used |= 1U << i;
            this->shader_shadow_samplers |= shadow << i;
         }
      } else {
         uniform->sampler[shader_type].index = ~0;
         uniform->sampler[shader_type].active = false;
      }
   }
