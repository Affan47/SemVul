set_one_motion_impl( const int id, const int mode, const std::string& name, const std::string& str_motion )
{
    if( name.empty() || str_motion.empty() ) return;

#ifdef _DEBUG
    std::cout << "MouseConfig::set_one_motion_impl " << name << std::endl;
    std::cout << "motion = " << str_motion << std::endl;
    std::cout << CONTROL::get_label( id  ) << std::endl;
#endif

    const bool ctrl = false;
    const bool shift = false;
    const bool alt = false;
    const guint motion = atoi( str_motion.c_str() );
    const bool dblclick = false;
    const bool trpclick = false;

    vec_items().push_back( MouseKeyItem( id, mode, name, str_motion, motion, ctrl, shift, alt, dblclick, trpclick ) );
}
