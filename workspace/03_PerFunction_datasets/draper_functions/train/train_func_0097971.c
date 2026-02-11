save(YAML::Emitter& out, ConstFileTransformRcPtr t)
        {
            out << YAML::VerbatimTag("FileTransform");
            out << YAML::Flow << YAML::BeginMap;
            out << YAML::Key << "src" << YAML::Value << t->getSrc();
            const char * cccid = t->getCCCId();
            if(cccid && *cccid)
            {
                out << YAML::Key << "cccid" << YAML::Value << t->getCCCId();
            }
            out << YAML::Key << "interpolation";
            out << YAML::Value;
            save(out, t->getInterpolation());

            EmitBaseTransformKeyValues(out, t);
            out << YAML::EndMap;
        }
