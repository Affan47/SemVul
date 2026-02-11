cpp_example_erosion()
{
    CamImage source,dest;
    source.load_pgm("resources/chess.pgm");
    source.erode_square3(dest);
    dest.save_pgm("output/chess_erode_cpp.pgm");
}
