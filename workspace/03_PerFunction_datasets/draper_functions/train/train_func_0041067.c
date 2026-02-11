find_in_map( const std::map<HepMC::GenParticle*,int>& m,
				GenParticle* p) const {
        std::map<GenParticle*,int>::const_iterator iter = m.find(p);
        if ( iter == m.end() ) return 0;
        return iter->second;
    }
