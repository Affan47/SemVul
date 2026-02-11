save_descriptors_ascii( string filename )
{
   kutility::save(filename, m_dense_descriptors, m_h*m_w, m_descriptor_size );
}
