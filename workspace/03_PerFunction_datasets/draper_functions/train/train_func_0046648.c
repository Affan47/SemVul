exportDot(std::string filename) {
    std::ofstream outfile (filename.c_str());
    outfile << "graph ScanGraph" << std::endl;
    outfile << "{" << std::endl;
    for (size_t i=0; i<edges.size(); i++) {
      outfile << (edges[i]->first)->id
	      << " -- "
	      << (edges[i]->second)->id
	      << " [label="
	      << std::fixed << std::setprecision(2) << edges[i]->constraint.transLength()
	      << "]" << std::endl;
    }
    outfile << "}" << std::endl;
    outfile.close();
  }
