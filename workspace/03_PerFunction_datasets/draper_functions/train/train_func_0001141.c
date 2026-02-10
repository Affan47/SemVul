getAllFieldValues( std::ostream &o ) const
{
	o << mrpt::format("%.09f %.09f %02u %02u %02.03f %u",
		fields.longitude_degrees,
		fields.latitude_degrees,
		fields.UTCTime.hour,
		fields.UTCTime.minute,
		fields.UTCTime.sec,
		static_cast<unsigned int>(fields.validity_char=='A' ? 1:0)
		);
	return true;
}
