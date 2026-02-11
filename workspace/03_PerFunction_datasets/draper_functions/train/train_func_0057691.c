vbc_upcast(
    void const * const t
) const {

    const void_cast_detail::set_type & s
        = void_cast_detail::void_caster_registry::get_const_instance();
    void_cast_detail::set_type::const_iterator it;
    for(it = s.begin(); it != s.end(); ++it){

        if((*it)->m_base == m_base){

            if ((*it)->m_derived != m_derived){

                const void * t_new;
                t_new = void_upcast(*m_derived, *(*it)->m_derived, t);
                if(NULL != t_new)
                    return (*it)->upcast(t_new);
            }
        }
    }
    return NULL;
}
