ImgLoader( const std::string& file )
    : m_file( file ),
      m_width( 0 ),
      m_height( 0 ),
      m_stop( false ),
      m_y( 0 ),
      m_loadedlevel( LOADLEVEL_INIT )
{
#ifdef _DEBUG
    std::cout << "ImgLoader::ImgLoader file = " << m_file << std::endl;
#endif
}
