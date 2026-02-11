printDegrees(std::ostream& os, const Value& value, const ExifData*)
    {
        if (value.count() == 3) {
            std::ostringstream oss;
            oss.copyfmt(os);
            static const char* unit[] = { "deg", "'", "\"" };
            static const int prec[] = { 7, 5, 3 };
            int n;
            for (n = 2; n > 0; --n) {
                if (value.toRational(n).first != 0) break;
            }
            for (int i = 0; i < n + 1; ++i) {
                const int32_t z = value.toRational(i).first;
                const int32_t d = value.toRational(i).second;
                if (d == 0) return os << "(" << value << ")";

                double b = static_cast<double>(z)/d;
                const int p = z % d == 0 ? 0 : prec[i];
                os << std::fixed << std::setprecision(p) << b
                   << unit[i] << " ";
            }
            os.copyfmt(oss);
        }
        else {
            os << value;
        }

        return os;
    }
