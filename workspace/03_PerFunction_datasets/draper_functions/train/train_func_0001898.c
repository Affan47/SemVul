connected_partners( std::vector<HepMC::GenParticle*>* output, int code,
				   int code_index, int num_indices ) const
    {


    	if ( !m_particle_owner ) return;


	if ( m_particle_owner->end_vertex() ) {
	    for ( GenVertex::particle_iterator p
		     = m_particle_owner->end_vertex()->particles_begin(family);
		  p != m_particle_owner->end_vertex()->particles_end(family);
		  ++p ) {


		for ( int index = code_index; index!=code_index+num_indices;
		      ++index ){
		    if ( (*p)->flow(index)==code && not_in_vector(output,(*p)) ) {
			output->push_back(*p);
			(*p)->flow().connected_partners( output, code,
							 code_index,
							 num_indices );
		    }
		}
	    }
	}

	if ( m_particle_owner->production_vertex() ) {
	    for ( GenVertex::particle_iterator p
		      = m_particle_owner->production_vertex()->
		      particles_begin( family );
		  p != m_particle_owner->production_vertex()->
		      particles_end( family ); ++p ) {


		for ( int index = code_index; index!=code_index+num_indices;
		      ++index ){
		    if ( (*p)->flow(index)==code && not_in_vector(output,(*p)) ) {
			output->push_back(*p);
			(*p)->flow().connected_partners( output, code,
							 code_index,
							 num_indices );
		    }
		}
	    }
	}
    }
