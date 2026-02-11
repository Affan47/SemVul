save(YAML::Emitter& out, ConstExponentTransformRcPtr t)
        {
            out << YAML::VerbatimTag("ExponentTransform");
            out << YAML::Flow << YAML::BeginMap;

            std::vector<float> value(4, 0.0);
            t->getValue(&value[0]);
            out << YAML::Key << "value";
            out << YAML::Value << YAML::Flow << value;
            EmitBaseTransformKeyValues(out, t);
            out << YAML::EndMap;
        }
