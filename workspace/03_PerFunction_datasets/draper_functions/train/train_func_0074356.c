paint(Graphics &g, const YRect &r) {
        g.setColor(bg);
        g.fillRect(r.x(), r.y(), r.width(), r.height());
        g.setColor(normalFg);
        g.setFont(font);

        draw(g, fRoot);
    }
