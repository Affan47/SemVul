zFillUScoreVariant(zScanner* scanner,int map_idx,int block_idx,int var_idx,
								   int sum){
	zUScoreBlock*    block;
	zUScoreMap*      map;
	zScannerVariant* var;
	int              v;
	coor_t           size,i;

	map = &scanner->uscore_map[map_idx];
	block = &scanner->uscore[block_idx];
	var = map->vars[var_idx];

	v = zGetScannerVariantScoreIndex(var);
	if(sum){
		if(var->score_sum[v] != NULL) return var->score_sum[v];
	}
	else{
		if(var->score[v] != NULL) return var->score[v];
	}
	size = var->last_pos - var->first_pos + 1;


	if (CDS == scanner->model->type) {
		var->score_sum[v] = zMalloc(sizeof(score_t)*3*size,
									"zPreComputeScanner var->score[i] (CDS)");
		zFillCDSUScore(scanner,var->first_pos, size,
					   &(var->score_sum[v][0]),&(var->score_sum[v][size]),
					   &(var->score_sum[v][2*size]));
	}
	else{
		var->score[v] = zMalloc(sizeof(score_t)*size,
								"zPreComputeScanner var->score[i]");
		var->score_sum[v] = zMalloc(sizeof(score_t)*size,
									"zPreComputeScanner var->score_sum[i]");
		var->score[v][0] = scanner->score(scanner,var->first_pos);
		if(var->score[v][0] == 0){
			var->score_sum[v][0] = 0;
		}
		else{
			var->score_sum[v][0] = zGetUScore(scanner,var->first_pos-1) +
				var->score[v][0];
		}
		for(i = var->first_pos+1;i <= var->last_pos; i++){
			var->score[v][i - var->first_pos] = scanner->score(scanner,i);

			if(var->score[v][i-var->first_pos] == MIN_SCORE){
				var->score_sum[v][i - var->first_pos] = 0;
			}
			else{
				var->score_sum[v][i - var->first_pos] = var->score_sum[v][i-1-var->first_pos] +
					var->score[v][i - var->first_pos];
			}
		}
	}
	if(sum){
		return var->score_sum[v];
	}
	else{
		return var->score[v];
	}
}
