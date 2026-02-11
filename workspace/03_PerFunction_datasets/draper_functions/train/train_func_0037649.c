internal_build_points_map_from_scan2D(const mrpt::obs::CObservation2DRangeScan &obs, mrpt::maps::CMetricMapPtr &out_map, const void *insertOps)
{

	if (out_map)
		return;

	out_map = CSimplePointsMap::Create();

	if (insertOps)
		static_cast<CSimplePointsMap*>(out_map.pointer())->insertionOptions = *static_cast<const CPointsMap::TInsertionOptions*>(insertOps);

	out_map->insertObservation(&obs,NULL);
}
