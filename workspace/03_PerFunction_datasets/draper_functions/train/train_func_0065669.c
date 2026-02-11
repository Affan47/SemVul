loadFile (std::string filename, std::vector<Value> &args, StackFrame *stack, StaticLink *slink, Scope *scope, int sl, std::string outfile, std::ostream *output, std::istream *input) {
    std::vector<std::string> filenames;
    filenames.push_back (filename);
    return loadFile (filenames, args, stack, slink, scope, sl, outfile, output, input);
}
