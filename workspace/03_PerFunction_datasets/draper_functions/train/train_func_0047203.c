color_doubletuple_to_inttuple(const std::vector<double> doublecolor) {
    std::vector<int> intcolor(3);
    for (int i = 0; i < 3; i++) intcolor[i] = (int) (doublecolor[i] * 255.0);
    return intcolor;
}
