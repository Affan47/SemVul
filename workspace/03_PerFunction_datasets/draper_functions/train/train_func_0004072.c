current_energy(int true_ligand_atoms, int outlev, FILE *logFile)  {
	evals++;
	Real energy = probe_point.evaluate(Normal_Eval);
	Real rmsd = current_rmsd(true_ligand_atoms, outlev, logFile);

#ifdef VERBOSE
		fprintf(logFile, "state %d %.3f %.3f", evals, energy, rmsd);
		for (int i=0; i < dimensionality; i++) {
			fprintf(logFile, " %.3f", probe_point.gread(i).real);
		}
		fprintf(logFile,"\n");
#endif

	total_energy += energy;
	Boltzmann_sum += exp(-energy/RT_CONSTANT);
	Boltzmann_diff_sum += exp(-1.0*(energy - base_energy)/RT_CONSTANT);


	if (energy < min_energy) {
		min_energy = energy;
		min_energy_rmsd = rmsd;
	}

	int bin = (int)(rmsd/BIN_SIZE);
	if (bin < NUM_BINS) {
		bin_count[bin]++;
		bin_total_energy[bin] += energy;
		bin_Boltzmann_sum[bin] += exp(-energy/RT_CONSTANT);
		if (energy < bin_min_energy[bin]) bin_min_energy[bin] = energy;
		if (energy > bin_max_energy[bin]) bin_max_energy[bin] = energy;
	}

	if (energy < 0.0) {
		favorable_evals++;
		total_favorable_energy += energy;
		update_bounds();

		if (bin < NUM_BINS) {
			bin_count_favorable[bin]++;
			bin_total_favorable_energy[bin] += energy;
		}
	}
	return energy;
}
