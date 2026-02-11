RelationMapInitializePhase3(void)
{


	if (IsBootstrapProcessingMode())
		return;


	load_relmap_file(false);
}
