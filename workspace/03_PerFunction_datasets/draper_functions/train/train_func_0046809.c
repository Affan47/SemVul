renderToFile(const std::string& outputFilename)
{
    Image img(400,400);
    cout << "Tracing..." << endl;
    scene->render(img);
    cout << "Writing image to " << outputFilename << "..." << endl;
    img.write_png(outputFilename.c_str());
    cout << "Done." << endl;
}
