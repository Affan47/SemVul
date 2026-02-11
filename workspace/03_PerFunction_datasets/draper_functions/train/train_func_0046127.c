main(int argc, char **argv) {
  parse_args(argc, argv);

  Graph g(infile, type);

  g.clean(type);
  g.renumber(type);
  g.display_binary(outfile, type);
}
