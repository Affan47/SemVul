grabImageGetNextFile()
{
	if ( m_grab_imgs_prefix.empty() )
			return string();
	else 	return format( "%s%06u.png",m_grab_imgs_prefix.c_str(), m_grab_imgs_idx++ );
}
