reparameterize_path(PlannerInfo *root, Path *path,
					Relids required_outer,
					double loop_count)
{
	RelOptInfo *rel = path->parent;


	if (!bms_is_subset(PATH_REQ_OUTER(path), required_outer))
		return NULL;
	switch (path->pathtype)
	{
		case T_SeqScan:
			return create_seqscan_path(root, rel, required_outer);
		case T_SampleScan:
			return (Path *) create_samplescan_path(root, rel, required_outer);
		case T_IndexScan:
		case T_IndexOnlyScan:
			{
				IndexPath  *ipath = (IndexPath *) path;
				IndexPath  *newpath = makeNode(IndexPath);


				memcpy(newpath, ipath, sizeof(IndexPath));
				newpath->path.param_info =
					get_baserel_parampathinfo(root, rel, required_outer);
				cost_index(newpath, root, loop_count);
				return (Path *) newpath;
			}
		case T_BitmapHeapScan:
			{
				BitmapHeapPath *bpath = (BitmapHeapPath *) path;

				return (Path *) create_bitmap_heap_path(root,
														rel,
														bpath->bitmapqual,
														required_outer,
														loop_count);
			}
		case T_SubqueryScan:
			return create_subqueryscan_path(root, rel, path->pathkeys,
											required_outer);
		default:
			break;
	}
	return NULL;
}
