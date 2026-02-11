init_multiples() {
    vector<string> empty;

    keywords["above"] = keyword(empty, empty, false, ABOVE);
    keywords["top"] = keyword(empty, empty, false, TOP);
    keywords["bot"] = keywords["bottom"] =
	keyword(empty, empty, false, BOTTOM);
    keywords["left"] = keyword(empty, empty, false, LEFT);
    keywords["right"] = keyword(empty, empty, false, RIGHT);
    keywords["up"] = keyword(empty, empty, false, UP);
    keywords["down"] = keyword(empty, empty, false, DOWN);
    keywords["ljust"] = keyword(empty, empty, false, LJUST);
    keywords["rjust"] = keyword(empty, empty, false, RJUST);
    keywords["below"] = keyword(empty, empty, false, BELOW);
    keywords["aligned"] = keyword(empty, empty, false, ALIGNED);
    keywords["unaligned"] = keyword(empty, empty, false, UNALIGNED);
    keywords["clipped"] = keyword(empty, empty, false, CLIPPED);
    keywords["unclipped"] = keyword(empty, empty, false, UNCLIPPED);
    keywords["size"] = keyword(empty, empty, false, SIZE);
    keywords["in"] = keyword(empty, empty, false, IN);
    keywords["out"] = keyword(empty, empty, false, OUT);
    keywords["off"] = keyword(empty, empty, false, OFF);
    keywords["on"] = keywords["auto"] = keyword(empty, empty, false, ON);
    keywords["fill"] = keyword(empty, empty, false, FILL);
    keywords["invis"] = keyword(empty, empty, false, INVIS);
    keywords["solid"] = keyword(empty, empty, false, SOLID);
    keywords["dotted"] = keyword(empty, empty, false, DOTTED);
    keywords["dashed"] = keyword(empty, empty, false, DASHED);
    keywords["fillcolor"] = keyword(empty, empty, false, FILLCOLOR);
    keywords["color"] = keyword(empty, empty, false, COLOR);
    keywords["thickness"] = keyword(empty, empty, false, THICKNESS);

}
