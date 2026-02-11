main(int argc, char * * argv)
{
    try {
        run(argc, argv);
    } catch (Error & e) {
        std::cerr << e.msg() << std::endl;
        return 1;
    }
}
