tell() { return reading ? zfile.total_out : (writing ? zfile.total_in : -1); }
