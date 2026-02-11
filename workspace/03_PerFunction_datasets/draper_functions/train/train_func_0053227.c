getDescriptionAsText(std::ostream &o) const
{
	CObservation::getDescriptionAsText(o);
	o << "Homogeneous matrix for the sensor 3D pose, relative to robot base:\n";
	o << sensorPose.getHomogeneousMatrixVal() << "\n" << sensorPose << endl;

	o << format("Sensor min/max range: %.02f / %.02f m\n", minRange, maxRange );

	o << "Raw packet count: " << scan_packets.size() << "\n";
}
